CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 222;
	title = 22202;

	CNtlTSGroup
	{
		gid = 0;

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
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;252;1;";
			type = 0;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 22207;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCRace
			{
				raceflg = 2;
			}
			CDboTSClickNPC
			{
				npcidx = 4511601;
			}
			CDboTSCheckLvl
			{
				maxlvl = 13;
				minlvl = 5;
			}
			CDboTSCheckClrQst
			{
				or = "220;";
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
				conv = 22209;
				ctype = 1;
				idx = 4511601;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 22208;
				gtype = 2;
				area = 22201;
				goal = 22204;
				m0fz = "-2495.000000";
				m0widx = 1;
				sort = 22205;
				stype = 1;
				m0fy = "0.000000";
				grade = 132203;
				m0fx = "3722.000000";
				m0ttip = 22215;
				rwd = 100;
				taid = 1;
				title = 22202;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 0;
				idx0 = 2312101;
				cnt0 = 3;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = -1;
				taid = 3;
				esctype = 0;
				idx2 = -1;
			}
		}
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
				idx0 = 2312101;
				cnt0 = 11;
				cnt2 = 0;
				ectype = -1;
				etype = 1;
				idx1 = -1;
				taid = 1;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 22208;
			gtype = 2;
			oklnk = 2;
			area = 22201;
			goal = 22204;
			sort = 22205;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 22202;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 22214;
			nextlnk = 101;
			rwdtbl = 22201;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4511601;
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

