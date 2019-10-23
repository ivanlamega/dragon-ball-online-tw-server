CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 194;
	title = 19402;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 3;
			elnk = 252;
			nextlnk = 4;
			prelnk = "2;";

			CDboTSActRegQInfo
			{
				cont = 19408;
				gtype = 3;
				area = 19401;
				goal = 19404;
				grade = 132203;
				rwd = 100;
				sort = 19405;
				stype = 2;
				taid = 1;
				title = 19402;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 0;
				idx0 = 2914100;
				cnt0 = 2;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = -1;
				taid = 2;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContGCond
		{
			cid = 5;
			prelnk = "4;";
			nolnk = 255;
			rm = 0;
			yeslnk = 100;

			CDboTSCheckSToCEvt
			{
				itype = 0;
			}
		}
		CDboTSContGAct
		{
			cid = 4;
			elnk = 252;
			nextlnk = 5;
			prelnk = "3;";

			CDboTSActWorldPlayScript
			{
				sid = 43;
				start = 1;
				taid = 1;
				uof = 1;
			}
		}
		CDboTSContGAct
		{
			cid = 101;
			elnk = 255;
			nextlnk = 254;
			prelnk = "100;";

			CDboTSActWorldPlayScript
			{
				sid = 43;
				start = 0;
				taid = 2;
				uof = 0;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 0;
				idx0 = -1;
				cnt0 = 0;
				cnt2 = 0;
				ectype = -1;
				etype = 1;
				idx1 = -1;
				taid = 1;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "101;";
			type = 1;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 19414;
			nextlnk = 101;
			rwdtbl = 19401;
			rwdtype = 0;
			ltime = -1;
			prelnk = "5;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4511101;
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;2;252;";
			type = 0;
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "4;3;";
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 19407;
			nolnk = 253;
			rm = 0;
			yeslnk = 2;

			CDboTSClickNPC
			{
				npcidx = 3174101;
			}
			CDboTSCheckPCCls
			{
				clsflg = 3;
			}
			CDboTSCheckLvl
			{
				maxlvl = 16;
				minlvl = 8;
			}
			CDboTSCheckPCRace
			{
				raceflg = 1;
			}
			CDboTSCheckClrQst
			{
				and = "43;";
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 2;
			cont = 19408;
			gtype = 3;
			oklnk = 3;
			area = 19401;
			goal = 19404;
			sort = 19405;
			prelnk = "0;";
			ds = 0;
			grade = 132203;
			rwd = 100;
			title = 19402;
		}
	}
}

