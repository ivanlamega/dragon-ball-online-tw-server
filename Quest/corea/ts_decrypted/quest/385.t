CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 385;
	title = 38502;

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
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 38509;
				ctype = 1;
				idx = 4751205;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 38508;
				gtype = 0;
				area = 38501;
				goal = 38504;
				m0fz = "-1944.000000";
				m0widx = 1;
				sort = 38505;
				stype = 1;
				m0fy = "0.000000";
				grade = 132203;
				m0fx = "5359.000000";
				m0ttip = 38515;
				rwd = 100;
				taid = 1;
				title = 38502;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 0;
				idx0 = 4031101;
				cnt0 = 10;
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
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 38514;
			nextlnk = 101;
			rwdtbl = 38501;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4751205;
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "1;252;0;";
			type = 0;
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
			cont = 38508;
			gtype = 0;
			oklnk = 2;
			area = 38501;
			goal = 38504;
			sort = 38505;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 38502;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 38507;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 4751205;
			}
			CDboTSCheckPCRace
			{
				raceflg = 2;
			}
			CDboTSCheckLvl
			{
				maxlvl = 23;
				minlvl = 15;
			}
		}
	}
}

