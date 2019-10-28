CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 439;
	title = 43902;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 101;
			elnk = 255;
			nextlnk = 254;
			prelnk = "100;";

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
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "101;";
			type = 1;
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 43908;
			gtype = 2;
			oklnk = 2;
			area = 43901;
			goal = 43904;
			sort = 43905;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 43902;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 43914;
			nextlnk = 101;
			rwdtbl = 43901;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4151201;
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;252;1;";
			type = 0;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 43907;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 4151201;
			}
			CDboTSCheckPCRace
			{
				raceflg = 4;
			}
			CDboTSCheckLvl
			{
				maxlvl = 16;
				minlvl = 8;
			}
			CDboTSCheckClrQst
			{
				and = "438;";
			}
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 43909;
				ctype = 1;
				idx = 4151201;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 43908;
				gtype = 2;
				area = 43901;
				goal = 43904;
				m0fz = "-2945.000000";
				m0widx = 1;
				sort = 43905;
				stype = 1;
				m0fy = "0.000000";
				grade = 132203;
				m0fx = "6127.000000";
				m0ttip = 43915;
				rwd = 100;
				taid = 1;
				title = 43902;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 0;
				idx0 = 4711100;
				cnt0 = 8;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = -1;
				taid = 3;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContGCond
		{
			cid = 3;
			prelnk = "2;";
			nolnk = 255;
			rm = 0;
			yeslnk = 100;

			CDboTSCheckSToCEvt
			{
				itype = 0;
			}
		}
	}
}

