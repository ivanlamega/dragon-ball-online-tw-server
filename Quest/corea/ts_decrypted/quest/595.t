CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 595;
	title = 59502;

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
			prelnk = "100;";
			type = 1;
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "1;0;252;";
			type = 0;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 59507;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCRace
			{
				raceflg = 4;
			}
			CDboTSClickNPC
			{
				npcidx = 7071103;
			}
			CDboTSCheckLvl
			{
				maxlvl = 20;
				minlvl = 10;
			}
			CDboTSCheckClrQst
			{
				and = "594;";
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
				conv = 59509;
				ctype = 1;
				idx = 7071103;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 59508;
				gtype = 2;
				area = 59501;
				goal = 59504;
				grade = 132203;
				rwd = 100;
				sort = 59505;
				stype = 1;
				taid = 1;
				title = 59502;
			}
		}
		CDboTSContGCond
		{
			cid = 3;
			prelnk = "2;";
			nolnk = 255;
			rm = 0;
			yeslnk = 100;

			CDboTSSlotMachine
			{
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 59514;
			nextlnk = 254;
			rwdtbl = 59501;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 7071103;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 59508;
			gtype = 2;
			oklnk = 2;
			area = 59501;
			goal = 59504;
			sort = 59505;
			prelnk = "0;";
			ds = 1;
			grade = 0;
			rwd = 100;
			title = 59502;
		}
	}
}

