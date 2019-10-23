CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 316;
	title = 31602;

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
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;252;1;";
			type = 0;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 31607;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCRace
			{
				raceflg = 2;
			}
			CDboTSClickNPC
			{
				npcidx = 4511208;
			}
			CDboTSCheckLvl
			{
				maxlvl = 24;
				minlvl = 16;
			}
			CDboTSCheckClrQst
			{
				and = "310;";
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
				conv = 31609;
				ctype = 1;
				idx = 4511208;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 31608;
				m1fx = "4252.000000";
				area = 31601;
				goal = 31604;
				m0fz = "-1921.000000";
				m0widx = 1;
				m1fy = "0.000000";
				m1ttip = 31616;
				sort = 31605;
				stype = 2;
				m0fy = "0.000000";
				m1fz = "-1943.000000";
				grade = 132203;
				m0fx = "4463.000000";
				m0ttip = 31615;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 31602;
				gtype = 3;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 1;
				eitype = 0;
				idx0 = 5811100;
				cnt0 = 15;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = 5812101;
				taid = 3;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 31614;
			nextlnk = 101;
			rwdtbl = 31601;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4511208;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 31608;
			gtype = 3;
			oklnk = 2;
			area = 31601;
			goal = 31604;
			sort = 31605;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 31602;
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

