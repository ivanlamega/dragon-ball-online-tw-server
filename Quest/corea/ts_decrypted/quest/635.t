CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 635;
	title = 63502;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 4;
			elnk = 255;
			nextlnk = 100;
			prelnk = "3;";

			CDboTSActPortal
			{
				dx = "0.000000";
				px = "5902.000000";
				widx = 1;
				dy = "0.000000";
				py = "0.000000";
				taid = 1;
				type = 0;
				dz = "0.000000";
				pz = "531.000000";
			}
		}
		CDboTSContGCond
		{
			cid = 3;
			prelnk = "2;";
			nolnk = 255;
			rm = 0;
			yeslnk = 4;

			CDboTSClickNPC
			{
				npcidx = 4261102;
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
				conv = 63509;
				ctype = 1;
				idx = 4261102;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 63508;
				gtype = 1;
				area = 63501;
				goal = 63504;
				grade = 132203;
				rwd = 100;
				sort = 63505;
				stype = 2;
				taid = 1;
				title = 63502;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 63514;
			nextlnk = 254;
			rwdtbl = 63501;
			rwdtype = 0;
			ltime = -1;
			prelnk = "4;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4141101;
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "100;";
			type = 1;
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 63508;
			gtype = 1;
			oklnk = 2;
			area = 63501;
			goal = 63504;
			sort = 63505;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 63502;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 63507;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 4261102;
			}
			CDboTSCheckLvl
			{
				maxlvl = 29;
				minlvl = 21;
			}
			CDboTSCheckPCRace
			{
				raceflg = 4;
			}
			CDboTSCheckClrQst
			{
				and = "634;";
			}
		}
	}
}

